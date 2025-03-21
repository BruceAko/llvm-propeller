## Artifact Evaluation

Hardware requirements
```
Intel Skylake or newer.
32 GB of RAM or more.
Access to hardware performance counters using linux perf.
```

To run the experiments for Artifact Evaluation
```
# sudo su
$ cd llvm-propeller/ArtifactEvaluation
$ CC=clang-20 CXX=clang++-20 Scripts/optimize_clang.sh

# Generate heatmap
$ Scripts/gen_heatmap.sh

# Expected contents of Results
# Contents of Results
$ Results
    mem_bolt_profile_conversion.txt
    mem_propeller_profile_conversion.txt
    mem_bolt_rewrite.txt
    mem_propeller_build.txt
    perf_clang_baseline.txt
    perf_clang_propeller.txt
    perf_clang_bolt.txt
    clang-fdo-heatmap.png
    clang-propeller-heatmap.png
    clang-bolt-heatmap.png
    sizes_clang.txt
```
