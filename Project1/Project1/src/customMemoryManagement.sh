#!/bin/bash
#SBATCH --job-name=CustomMemoryManagement       	# the name of your job
#SBATCH --output=/scratch/cb2693/CustomMemManage.out    # this is the file your output and errors go to
#SBATCH --time=2-0:00:00                        	# 20 min, shorter time, quicker start, max run time 
#SBATCH --workdir=/home/cb2693                  	# your work directory
#SBATCH --mem=80000                             	# 20GB of memory

module load gcc
cd /home/cb2693/LSDS_Final_Project/Project1/Project1/src/
srun make
cd ../bin/
srun pt_custom.exe
srun pt_os.exe

