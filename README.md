Clone with the pybind11 submodule:

```
git clone --recurse-submodules https://github.com/jmeyers314/pyOffloadDemo.git
```

Setup Cori-GPU

```
module purge && module load esslurm PrgEnv-llvm/10.0.0-git_20190828 python3
salloc -C gpu -N 1 -t 30 -c 10 --gres=gpu:1 -A m1759
```

Compile on Cori-GPU

```
clang++ -O3 -Wall -Wno-unused-value -shared -std=c++14 -fPIC -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -Ipybind11/include -I/usr/common/software/python/3.7-anaconda-2019.07/include/python3.7m demo.cpp -o _demo`python3-config --extension-suffix`
```

Test

```
srun python demo.py
```
