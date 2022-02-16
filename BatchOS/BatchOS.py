import os
import time


jobsDirectory = "/home/inheritest/user/batch/jobs"
running = True
while(running):

    print("Would you like to:")
    print("1. List jobs")
    print("2. Set Jobs Directory")
    print("3. Compile and run a specific program")
    print("4. Compile and run all jobs in a specific directory")
    print("5. Shutdown")
    print("6. List program options")
    print("7. Help")
    userInput = input("Enter you choice: ")
    time.sleep(1)

    if(int(userInput) == 1):
        jobs = os.listdir(jobsDirectory)
        for f in jobs:
             ending = f[len(f)-2]+f[len(f)-1]
             if (ending == ".c"):
                 print(f)

    if(int(userInput) == 2):
      jobsDirectory = input("Please enter the new directory: ")
      time.sleep(1)

    if(int(userInput) == 3):
     newInput = input("Enter the specific job you would like to run: ")
     time.sleep(1)
     specificJob = jobsDirectory + "/" + newInput
     nameOfCompiledFile = newInput.rstrip(".c")
     os.system("gcc -o " + nameOfCompiledFile + " " + specificJob)
     os.system("./" + nameOfCompiledFile)

    if(int(userInput) == 4):
        jobs = os.listdir(jobsDirectory)
        for f in jobs:
         ending = f[len(f)-2]+f[len(f)-1]
         if (ending == ".c"):
             specificJob = jobsDirectory + "/" + f
             nameOfCompiledFile = f.rstrip(".c")
             os.system("gcc -o " + nameOfCompiledFile + " " + specificJob)
             os.system("./" + nameOfCompiledFile)

    if(int(userInput) == 5):
         running = False

    if(int(userInput) == 6):
        print("The program options are as follows:")
        print("1. List jobs")
        print("2. Set Jobs Directory")
        print("3. Compile and run a specific program")
        print("4. Compile and run all jobs in a specific directory")
        print("5. Shutdown")
        print("6. List program options")
        print("7. Help")
    
    if(int(userInput) == 7):
         print("1. List Jobs: lists every job in the jobs directory")
         print("2. Set Jobs Directory: change the directory which your jobs are looked for default directory is /home/inheritest/user/batch/jobs")
         print("3. Compile and run a specific program: run a specific program in the jobs directory")
         print("4. Compile and run all jobs: run all the jobs in the jobs directory")
         print("5. Shutdown: terminates the program")
         print("6. List program options: lists out all options that can be selected in this program")
         print("7. Help: Elaborates what you can do with this program")
