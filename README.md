# CMPSC472 Project SmartCare Hospital Patient Scheduling Simulator

### Project Overview
SmartCare is a small simulator that applies CPU scheduling concepts to a real-world scenario in how hospitals decide the order in which patients are treated. In this simulator, each patient is modeled like an OS process with an arrival time, treatement (burst) time, and priority level. 
- The backend performs all scheduling calculations and the GUI provides visualization for results.
- For this project, there are 4 scheduling algorithms used, FCFS, SJF, Priority, and Round Robin.
- The goal of the project is to demonstrate how OS scheduling can be applied to improve medical workflow, efficiency, and fairness. 

#### Significance


### Structure of Code

**How To Run**
- To run the project - git clone repository to directory
- Install necessary libraries: streamlit using
  ```bash
  pip install streamlit
  ```
Then:
  ```bash
  gcc src\main.c src\fcfs.c src\sjf.c src\priority.c src\round_robin.c src\utils.c src\cJSON.c -I include -o scheduler.exe; echo "Build complete"
  ```
Then:

  ```bash
  cd gui
  python -m streamlit run app.py      
  ```


#### Diagran

![alt text]() 

![alt text]() 
![alt text]()


### Conclusion
