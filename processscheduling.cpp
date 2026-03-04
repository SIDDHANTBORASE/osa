#include <iostream>
#include <iomanip>
using namespace std;

void ganttchart(int n,int pid[],int bt[]){
    cout<<"\nGantt Chart:\n|";
    for(int i =0;i<n;i++)
        cout<<" P"<<pid[i]<<" |";
    
    cout<<"\n0";
    int time =0;
    for(int i =0;i<n;i++){
        time += bt[i];
        cout<<"  "<<time;
    }
    cout<<endl;
}

void fcfs(int n,int pid[],int wt[],int bt[],int tat[]){
    wt[0] = 0;

    for(int i =1; i < n; i++)
        wt[i] = wt[i-1] + bt[i-1];
    
    for(int i =0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    float totalwt=0, totaltat=0;

    cout<<"\nProcess\tBurst\tWaiting\tTurn Around\n";
    for(int i = 0; i < n; i++){
        cout<<"P"<<pid[i]<<"\t"<<bt[i]<<"\t"<<wt[i]<<"\t"<<tat[i]<<endl;
        totalwt += wt[i];
        totaltat += tat[i];
    }

    cout<<"\nAverage Waiting Time = "<< totalwt/n << endl;
    cout<<"Average Turnaround Time = "<< totaltat/n << endl;

    ganttchart(n,pid,bt);
}

void sjf(int n,int pid[],int wt[],int bt[],int tat[]){
    
    // Sort by Burst Time
    for(int i =0; i < n-1; i++){
        for(int j = i+1; j < n; j++){
            if(bt[i] > bt[j]){
                int temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    wt[0] = 0;
    for(int i =1; i < n; i++)
        wt[i] = wt[i-1] + bt[i-1];
    
    for(int i =0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    float totalwt=0, totaltat=0;

    cout<<"\nProcess\tBurst\tWaiting\tTurn Around\n";
    for(int i = 0; i < n; i++){
        cout<<"P"<<pid[i]<<"\t"<<bt[i]<<"\t"<<wt[i]<<"\t"<<tat[i]<<endl;
        totalwt += wt[i];
        totaltat += tat[i];
    }

    cout<<"\nAverage Waiting Time = "<< totalwt/n << endl;
    cout<<"Average Turnaround Time = "<< totaltat/n << endl;

    ganttchart(n,pid,bt);
}

void psm(int n,int pid[],int wt[],int bt[],int tat[], int priority[]){
    
    // Sort by Priority (Lower number = Higher priority)
    for(int i =0; i < n-1; i++){
        for(int j = i+1; j < n; j++){
            if(priority[i] > priority[j]){
                int temp;

                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
            else if(priority[i] == priority[j]){
                if(bt[i] > bt[j]){
                    int temp;

                    temp = bt[i];
                    bt[i] = bt[j];
                    bt[j] = temp;

                    temp = pid[i];
                    pid[i] = pid[j];
                    pid[j] = temp;
                }
            }
        }
    }

    wt[0] = 0;
    for(int i =1; i < n; i++)
        wt[i] = wt[i-1] + bt[i-1];
    
    for(int i =0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    float totalwt=0, totaltat=0;

    cout<<"\nProcess\tBurst\tPriority\tWaiting\tTurn Around\n";
    for(int i = 0; i < n; i++){
        cout<<"P"<<pid[i]<<"\t"<<bt[i]<<"\t"<<priority[i]<<"\t\t"<<wt[i]<<"\t"<<tat[i]<<endl;
        totalwt += wt[i];
        totaltat += tat[i];
    }

    cout<<"\nAverage Waiting Time = "<< totalwt/n << endl;
    cout<<"Average Turnaround Time = "<< totaltat/n << endl;

    ganttchart(n,pid,bt);
}

int main(){
    int n;

    cout<<"Enter the number of Processes: ";
    cin>>n;
    
    int *pid = new int[n];
    int *wt  = new int[n];
    int *bt  = new int[n];
    int *tat = new int[n];
    int *priority = new int[n];

    cout<<"Enter the Burst time of the Processes:"<<endl;
    for(int i =0; i<n; i++){
        cout<<"Process "<<i+1<<": ";
        cin>>bt[i];
        pid[i] = i+1;  
    }

    int choice;
    cout<<"\nEnter the Choice:\n";
    cout<<"1) FCFS\n";
    cout<<"2) SJF\n";
    cout<<"3) Priority Scheduling\n";
    cin>>choice;

    if(choice==1){
        fcfs(n,pid,wt,bt,tat);
    }
    else if(choice==2){
        sjf(n,pid,wt,bt,tat);
    }
    else if(choice==3){
        cout<<"Enter the Priority of the Processes (Lower number = Higher priority):"<<endl;
        for(int i =0; i<n; i++){
            cout<<"Process "<<i+1<<": ";
            cin>>priority[i];
        }

        psm(n,pid,wt,bt,tat,priority);
    }
    else{
        cout<<"Invalid Choice!"<<endl;
    }

    delete[] pid;
    delete[] wt;
    delete[] bt;
    delete[] tat;
    delete[] priority;

    return 0;
}
