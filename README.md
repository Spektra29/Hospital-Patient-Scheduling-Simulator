# CMPSC472 Project SmartCare Hospital Patient Scheduling Simulator

### Project Overview
SmartCare is a small simulator that applies CPU scheduling concepts to a real-world scenario in how hospitals decide the order in which patients are treated. In this simulator, each patient is modeled like an OS process with an arrival time, treatement (burst) time, and priority level. 
- The backend performs all scheduling calculations and the GUI provides visualization for results.
- For this project, there are 4 scheduling algorithms used, FCFS, SJF, Priority, and Round Robin.
- The goal of the project is to demonstrate how OS scheduling can be applied to improve medical workflow, efficiency, and fairness. 

#### Significance
Efficient patient scheduling is a major challenge in healthcare due to limited staff, emergencies, and unexpected arrivals. Long wait times affect safety and patient outcomes. This simulator shows how OS scheduling algorithms can be applied to hospital workflows to offer a simple model for improving patient flow. It lets users compare different algorithms, understand the tradeoffs, and explore resource allocation. Although simplified, this project highlights how computational methods can help improve fairness and efficiency in medical field.

### Structure of Code

#### Project Report
- Report is available to view in PDF format in the documentation folder in the repository (no download)
[Download Project Report]([./FinalReport.docx](https://github.com/Spektra29/Hospital-Patient-Scheduling-Simulator/blob/main/documentation/FinalProject_CMPSC472.docx))

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
![alt text](https://github.com/Spektra29/Hospital-Patient-Scheduling-Simulator/blob/main/images/472_diagram_smartcare.jpg) 

#### GUI Design and Results
![alt text](https://github.com/Spektra29/Hospital-Patient-Scheduling-Simulator/blob/main/images/472_smartcare_gui.jpg) 

![alt text](https://github.com/Spektra29/Hospital-Patient-Scheduling-Simulator/blob/main/images/472_smartcare_gui_results.jpg)
#### Demo Video
[Watch demo]([./demo.mp4](https://github.com/Spektra29/Hospital-Patient-Scheduling-Simulator/blob/main/Healthcare_Patient_Scheduler_Demo_simulation.mp4))


### Conclusion

This project demonstrated how operating system scheduling strategies can be applied to real healthcare challenges such as patient management and triage. By modeling patients as processes and applying FCFS, SJF, Priority Scheduling, and Round Robin, we gained insight into how scheduling decisions impact patient waiting times and resource allocation.
We learned how important algorithm choice is for fairness and efficiency, especially in high-stakes environments like hospitals. The project helped reinforce OS concepts such as waiting time, turnaround time, preemption, and process prioritization.

