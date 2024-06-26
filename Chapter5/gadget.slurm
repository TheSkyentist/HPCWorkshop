#! /bin/bash -l
# (Specifying -l runs as login shell)
#
# Line that start with #SBATCH will be read as SBATCH commands
# It can be helpful to delineate comments with ### Instead
#
# --------------------------------------------------------------
# Preamble: Requests resources to run your job.
# --------------------------------------------------------------
#
# 1) Set the job name
#SBATCH --job-name=Gadget
#
# SLURM reads %x as the job name and %j as the job ID %a as the array number
# 
# 2) Set the stdout and stderr
#SBATCH -o %x-%j.out
###SBATCH -e %x-%j.err # If we omit this, stderr just goes to stdout
# 
# 3) Get notifications
#SBATCH --mail-type=ALL
#SBATCH --mail-user=hviding@mpia.de
#
# 4) Request Resources
#SBATCH --nodes=1 # Number of Nodes we request
#SBATCH --ntasks-per-node=10 # Number of processes per node
#SBATCH --cpus-per-task=1 # Number of threads per process
#SBATCH --ntasks-per-core=1 # Number of SMTs per core (Can either be 1 or 2 or ONLY 1)
#SBATCH --mem=16GB
#SBATCH --time 00:00:01 # Maximum wall-time of our program (HH:MM:DD)
#
# --------------------------------------------------------------
# Main Body: Run the job
# --------------------------------------------------------------

# Purge any existing modules
module purge

# Load any necessary modules
module load apptainer

# Run our code
apptainer exec gadget_latest.sif mpirun -np 2 /usr/src/app/gadget4/examples/G2-galaxy/Gadget4 param.txt