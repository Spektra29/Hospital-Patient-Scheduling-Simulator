import json
import subprocess
import tempfile
import os

EXEC_NAME = "../scheduler"   # adjust if needed

def run_scheduler(data):
    # Save input as temporary JSON file
    with tempfile.NamedTemporaryFile(mode="w", delete=False, suffix=".json") as f:
        json.dump(data, f)
        temp_input = f.name


    # Call the scheduler executable
    result = subprocess.run(
        [EXEC_NAME, temp_input],
        capture_output=True,
        text=True
    )

    # Delete temp file
    os.remove(temp_input)

    if result.returncode != 0:
        return {"error": result.stderr}

    # Parse JSON output from C
    try:
        return json.loads(result.stdout)
    except:
        return {"error": "Invalid output from C program", "raw": result.stdout}
