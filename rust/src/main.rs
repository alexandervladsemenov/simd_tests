use std::env;
use std::time::Instant;
use rand::Rng;

fn main() {
    let args: Vec<String> = env::args().collect();

    let mut n = 10_000;
    let mut sigma = 1.0_f32;
    let mut radius = 3;

    if args.len() > 1 {
        n = args[1].parse().unwrap_or(n);
    }
    if args.len() > 2 {
        radius = args[2].parse().unwrap_or(radius);
    }
    if args.len() > 3 {
        sigma = args[3].parse().unwrap_or(sigma);
    }

    let sample_size = n * n;
    let mut array = vec![0.0_f32; sample_size];
    let mut results = vec![0.0_f32; sample_size];
    let mut weights = vec![0.0_f32; (2 * radius + 1) * (2 * radius + 1)];

    let mut rng = rand::thread_rng();
    for i in 0..sample_size {
        array[i] = rng.gen::<f32>();
    }

    let start = Instant::now();
    let mut total_count = 0_u64;

    for i in 0..n {
        for j in 0..n {
            let imax = (i + radius).min(n - 1);
            let imin = i.saturating_sub(radius);
            let jmax = (j + radius).min(n - 1);
            let jmin = j.saturating_sub(radius);
            let index_global = n * i + j;

            let mut idx = 0;
            for ii in imin..=imax {
                for jj in jmin..=jmax {
                    let index_local = n * ii + jj;
                    let diff = array[index_global] - array[index_local];
                    weights[idx] = (-diff * diff / (sigma * sigma * 2.0)).exp();
                    idx += 1;
                }
            }

            results[index_global] = 0.0;
            let mut weight = 0.0;
            idx = 0;

            for ii in imin..=imax {
                for jj in jmin..=jmax {
                    total_count += 1;
                    let index_local = n * ii + jj;
                    let w = weights[idx];
                    weight += w;
                    results[index_global] += array[index_local] * w;
                    idx += 1;
                }
            }

            results[index_global] /= weight;
        }
    }

    let duration = start.elapsed();
    println!("CPU Time: {} ms", duration.as_millis());
    println!("Average {}", results.into_iter().sum::<f32>()/sample_size as f32);
    println!("Total Count {}", total_count);
}
