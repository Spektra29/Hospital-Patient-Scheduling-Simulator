import json
import subprocess
import tempfile
import os
import sys

# Get the directory of this script
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
# The scheduler executable is one level up
EXEC_NAME = os.path.join(os.path.dirname(SCRIPT_DIR), "scheduler.exe")

def run_scheduler(data):
    # Save input as temporary JSON file
    with tempfile.NamedTemporaryFile(mode="w", delete=False, suffix=".json") as f:
        json.dump(data, f)
        temp_input = f.name

    try:
        # Call the scheduler executable
        result = subprocess.run(
            [EXEC_NAME, temp_input],
            capture_output=True,
            text=True,
            timeout=30  # increased timeout to allow longer simulations
        )

        if result.returncode != 0:
            return {"error": f"Scheduler error: {result.stderr}", "stdout": result.stdout}

        # Parse JSON output from C
        try:
            output = json.loads(result.stdout)
            return output
        except json.JSONDecodeError as e:
            return {"error": f"Invalid JSON from scheduler: {str(e)}", "raw": result.stdout}

    except FileNotFoundError:
        return {"error": f"Scheduler executable not found at: {EXEC_NAME}"}
    except subprocess.TimeoutExpired as e:
        # Include any partial output to help debugging
        return {"error": f"Scheduler timed out after {e.timeout} seconds", "stdout": e.stdout, "stderr": e.stderr}
    except Exception as e:
        return {"error": f"Error running scheduler: {str(e)}"}
    finally:
        # Delete temp file
        try:
            os.remove(temp_input)
        except:
            pass
