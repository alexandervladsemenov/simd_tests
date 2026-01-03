use std::env;
use std::time::Instant;
use rand::Rng;

fn main() {
    let args: Vec<String> = env::args().collect();

    let n = if args.len() > 1 {
        args[1].parse().unwrap_or(10_000)
    } else {
        10_000
    };

    let radius = if args.len() > 2 {
        args[2].parse().unwrap_or(3)
    } else {
        3
    };

    let sigma = if args.len() > 3 {
        args[3].parse().unwrap_or(1.0)
    } else {
        1.0_f32
    };

    let mut array = vec![0.0_f32; n * n];
    let mut results = vec![0.0_f32; n * n];

    let mut rng = rand::thread_rng();
    for val in array.iter_mut() {
        *val = rng.gen::<f32>();
    }

    let sample_size = (n * n) as f32;
    let start = Instant::now();
    let mut total_count = 0_u64;

    let sigma_sq_inv = -0.5_f32 / (sigma * sigma);

    for i in 0..n {
        let imin = i.saturating_sub(radius);
        let imax = (i + radius).min(n - 1);
        let actual_rows = imax - imin + 1;

        for j in 0..n {
            let jmin = j.saturating_sub(radius);
            let jmax = (j + radius).min(n - 1);
            let actual_cols = jmax - jmin + 1;
            let index_global = n * i + j;
            let center_val = array[i * n + j];
            let mut sum_weights = 0.0_f32;
            let mut sum_weighted = 0.0_f32;

            for ii in 0..actual_rows {
                let actual_row = imin + ii;
                let row_start = actual_row * n + jmin;

                for jj in 0..actual_cols {
                    let neighbor_val = array[row_start + jj];
                    let diff = center_val - neighbor_val;
                    let diff_sq = diff * diff;
                    let weight = (diff_sq * sigma_sq_inv).exp();

                    sum_weights += weight;
                    sum_weighted += weight * neighbor_val;
                    total_count += 1;
                }
            }

            results[index_global] = sum_weighted / sum_weights;
        }
    }

    let duration = start.elapsed();

    println!("CPU Time: {} ms", duration.as_millis());
    println!("Average {}", results.iter().map(|&x| x as f64).sum::<f64>()/ sample_size as f64);
    println!("Total Count {}", total_count);

   }