#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
    FILE *jobs;
    char string[80];
    int pId[20], arrival[20], cpuBurst[20], priority[20], completion[20];
    int j;
    int nJobs;

    for(int x = 0; x < 20; x ++)
    {
        pId[x] = 0;
        arrival[x] = 0;
        cpuBurst[x] = 0;
        priority[x] = 0;
        completion[x] = 0;
    }
    /* Open file of jobs to be put in the ready que. */
    jobs = fopen("input.txt", "r");
    /* Load the ready que from the file. */
    //fgets(string,1000, jobs);
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    j = 0;
    while (fgets(buffer, MAX_LENGTH, jobs)) // Loop to read through the txt file setting buffer = a line of my txt file "input.txt"
    {
        int count = 0; // Used to keep track of the order that the input is in so if count == 0 then we are storing integers found in pId ect.
        for(int x = 0; x < strnlen(buffer, 100); x++)
        {
            int num = buffer[x] - 48; //File is reading text so giving the ascii value of numbers so we subtract 48, the ascii value of zero, to convert them to integers
            if(num == -16 || num == -38)
            {
                count++;
                
            }
            else if(count == 0 && j != 0)
            {
                int temp = pId[j];
                unsigned pow = 10;// Method I found online of concatonating integers in C
                while(num >= pow)
                    pow *= 10;
                temp = temp * pow + num; 
                pId[j] = temp;
            }
            else if(count == 1 && j!=0)
            {
                int temp = arrival[j];
                unsigned pow = 10;
                while(num >= pow)
                    pow *= 10;
                temp = temp * pow + num;
                arrival[j] = temp;
                
            }
            else if(count == 2 && j!=0)
            {
                int temp = cpuBurst[j];
                unsigned pow = 10;
                while(num >= pow)
                    pow *= 10;
                temp = temp * pow + num;
                cpuBurst[j] = temp;
                /*printf("num :%d ", num);
                printf("temp :%d ", temp);*/
            }
            else if(count == 3 && j!=0)
            {
                int temp = priority[j];
                unsigned pow = 10;
                while(num >= pow)
                    pow *= 10;
                temp = temp * pow + num;
                priority[j] = temp;
            }

        }
        j = j+1;
        
    }
    nJobs = j - 1;
    
    
    printf("\n");
    printf("number of jobs = %d \n", nJobs);
    fclose(jobs);


    //First come first served
    
    float tPut, turn, resp;
    turn = 0.0f;
    resp = 0.0f;
    int start;
    
    printf("Terminated Jobs. (First Come, First Served). \n");
    printf("processId   arrival completion\n");
    for(int x = 1; x < nJobs+1; x++)
    {
        if(arrival[x] > completion[x-1])
            start = (arrival[x]);
            
        else
            start = completion[x-1];    
        completion[x] = start + cpuBurst[x];
        turn = turn + (completion[x] - arrival[x]);
        resp = resp + (start - arrival[x]);

        printf("%d          %d      %d \n", pId[x], arrival[x], completion[x]);
    }
    tPut = (float) nJobs/ (float)completion[nJobs];
    turn = turn/(float)nJobs;
    resp = resp/(float)nJobs;
    printf("Run Stats\n");
    printf("Throughput = %f \n", tPut);
    printf("Average turnaround time = %f \n", turn);
    printf("Average response time = %f \n", resp);
    


    // Shortest Jobs First
    turn = 0.0f;
    resp = 0.0f;
    start;
    int shortest;
    int time = 0;
    int used[nJobs + 1];
    int order [nJobs+1];
    int current = 0;
    int temp;
    int i;
    used[1] = 1;
    for(int x = 0; x < nJobs+1; x++)
    {
        order[x] = x;
        completion[x] = 0;
    }
        
    int n = sizeof(order)/sizeof(order[0]);
    for (i = 0; i < n-1; i++)      
       for (j = 0; j < n-i-1; j++)
           if (cpuBurst[order[j]] > cpuBurst[order[j+1]])
            {
                temp = order[j];
                order[j] = order[j+1];
                order[j+1] = temp;
            }
    for(int x = 0; x < nJobs+1; x++)
    {
        used[x] = 0;
    }
    
    printf("Terminated Jobs. (Shortest Jobs First). \n");
    printf("processId   arrival completion\n");
    
    for(int x = 1; x < nJobs+1; x++)
    {
        j = x;
        if(arrival[j] < time)
        {
            for(j = 1; j < nJobs+1; j++)
            {
                if(arrival[order[j]] < time && used[order[j]] == 0)
                {
                    j = order[j];
                    start = completion[current];
                    current = j;
                    used[j] = 1;

                    break;
                }
            }
        }   
        else if(used[j] == 1)
        {
            for(j = 1; j < nJobs; j++)
            {
                if(used[j] != 1)
                {
                    printf("hit");
                    start = completion[current];
                    current = j;
                    used[j] = 1;
                }
            }
        }
        else
        {
            start = completion[j-1];  
            used[j] = 1;
            current = j;
        }
        time = time + cpuBurst[j];  
        completion[j] = start + cpuBurst[j];
        turn = turn + (completion[j] - arrival[j]);
        resp = resp + (start - arrival[j]);

        printf("%d          %d      %d \n", pId[j], arrival[j], completion[j]);
    }
    tPut = (float) nJobs/ (float)completion[nJobs];
    turn = turn/(float)nJobs;
    resp = resp/(float)nJobs;
    printf("Run Stats\n");
    printf("Throughput = %f \n", tPut);
    printf("Average turnaround time = %f \n", turn);
    printf("Average response time = %f \n", resp);
    


    //Round Robin
    int tq = 10;
    int completed[nJobs+1];
    time = 0;
    int starts[nJobs+1];
    for(int x = 0; x < nJobs+1; x++)
    {
        completed[x] = 0;
        starts[x] = -1;
    }
    int allCompleted = 0;
    printf("Terminated Jobs. (Round Robin). \n");
    printf("processId   arrival completion\n");
    while(allCompleted != 1)
    {
        allCompleted = 1;
        for(int x = 1; x < nJobs+1; x++)
        {
            if(completed[x] != 1 && arrival[x] <= time)
            {
                if(starts[x] == -1)
                {
                    starts[x] = time;
                }
                if(cpuBurst[x] <= tq)
                {
                    time = time + cpuBurst[x];
                    completion[x] = time;
                    completed[x] = 1;
                    turn = turn + (completion[x] - arrival[x]);
                    resp = resp + (starts[x] - arrival[x]);
                    printf("%d          %d      %d \n", pId[x], arrival[x], completion[x]);
                }
                else
                {
                    cpuBurst[x] = cpuBurst[x] - tq;
                    time = time + tq;
                }
                allCompleted = 0;
            }
        }

        
    }
    tPut = (float) nJobs/ (float)time;
    turn = turn/(float)nJobs;
    resp = resp/(float)nJobs;
    printf("Run Stats\n");
    printf("Throughput = %f \n", tPut);
    printf("Average turnaround time = %f \n", turn);
    printf("Average response time = %f \n", resp);

    return(0);
}
