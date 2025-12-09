import streamlit as st
from scheduler_runner import run_scheduler

st.set_page_config(
    page_title="Patient Scheduler",
    layout="centered"
)

st.title("🏥 Patient Scheduling Simulator")

st.write("This GUI sends your input to a C backend and displays the scheduling results.")

num_patients = st.number_input("Number of patients", min_value=1, max_value=50, step=1)

patients = []

st.subheader("Enter Patient Information")

for i in range(num_patients):
    st.write(f"### Patient {i+1}")
    pid = st.text_input(f"ID {i+1}", value=f"P{i+1}")
    arrival = st.number_input(f"Arrival Time {i+1}", min_value=0, key=f"arr{i}")
    burst = st.number_input(f"Burst Time {i+1}", min_value=1, key=f"bur{i}")
    priority = st.number_input(f"Priority {i+1}", min_value=1, max_value=10, key=f"pri{i}")

    patients.append({
        "id": pid,
        "arrival": arrival,
        "burst": burst,
        "priority": priority
    })

algorithm = st.selectbox(
    "Select scheduling algorithm",
    ["FCFS", "SJF", "Priority", "Round Robin"]
)

quantum = None
if algorithm == "Round Robin":
    quantum = st.number_input("Time Quantum", min_value=1)

if st.button("Run Scheduler"):
    request = {
        "algorithm": algorithm,
        "quantum": quantum if quantum else 0,
        "patients": patients
    }

    result = run_scheduler(request)

    if "error" in result:
        st.error(result["error"])
    else:
        st.success("Scheduling Complete!")

        st.subheader("Execution Order")
        order = result.get("order", [])
        st.write(order)

        st.subheader("Waiting Times")
        st.json(result.get("waiting_times", {}))

        st.subheader("Turnaround Times")
        st.json(result.get("turnaround_times", {}))

        st.subheader("Average Waiting Time")
        st.write(result.get("avg_waiting", 0))

        st.subheader("Average Turnaround Time")
        st.write(result.get("avg_turnaround", 0))
