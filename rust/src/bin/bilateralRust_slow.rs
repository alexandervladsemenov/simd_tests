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

       for i in 0..n {
           for j in 0..n {
               let imax = (i + radius).min(n - 1);
               let imin = i.saturating_sub(radius);
               let jmax = (j + radius).min(n - 1);
               let jmin = j.saturating_sub(radius);
               let index_global = n * i + j;
               let center_val = array[i * n + j];
               let mut sum_weights = 0.0_f32;
               let mut sum_weighted = 0.0_f32;

               for ii in imin..=imax {
                   for jj in jmin..=jmax {
                       total_count += 1;
                       let index_local = n * ii + jj;
                       let diff = center_val - array[index_local];
                       let w = (-diff * diff / sigma / sigma / 2.0).exp();
                       sum_weights += w;
                       sum_weighted += array[index_local] * w;
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
