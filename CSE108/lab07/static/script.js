const BASE_URL = "/grades";

// Helper function to display messages
function showMessage(elementId, message, isError = false) {
    const el = document.getElementById(elementId);
    el.textContent = message;
    el.className = "result " + (isError ? "error" : "success");
}

// Helper function to encode student name safely 
function encodeName(name) {
    return encodeURIComponent(name.trim());
}

// Load All Grades
document.getElementById("btn-load-all").addEventListener("click", async () => {
    try {
        const response = await fetch(BASE_URL);
        if (!response.ok) throw new Error("Failed to fetch grades");
        const data = await response.json();
        
        const tbody = document.getElementById("grades-body");
        tbody.innerHTML = ""; // Clear existing rows

        // Handle both array and object formats depending on API response
        const students = Array.isArray(data) ? data : Object.entries(data).map(([name, grade]) => ({ name, grade }));

        if (students.length === 0) {
            tbody.innerHTML = "<tr><td colspan='2'>No students found.</td></tr>";
            return;
        }

        students.forEach(student => {
            const row = document.createElement("tr");
            row.innerHTML = `<td>${student.name}</td><td>${student.grade}</td>`;
            tbody.appendChild(row);
        });
    } catch (error) {
        console.error(error);
        showMessage("get-result", "Error loading grades: " + error.message, true);
    }
});

// Get Specific Student Grade
document.getElementById("btn-get").addEventListener("click", async () => {
    const name = document.getElementById("get-name").value;
    if (!name) return showMessage("get-result", "Please enter a student name.", true);

    try {
        const response = await fetch(`${BASE_URL}/${encodeName(name)}`);
        if (!response.ok) throw new Error("Student not found");
        const data = await response.json();
        
        // Display neatly, not raw JSON
        const grade = data.grade !== undefined ? data.grade : data[Object.keys(data)[0]];
        showMessage("get-result", `Student: ${name}, Grade: ${grade}`);
    } catch (error) {
        showMessage("get-result", "Error: " + error.message, true);
    }
});

// Create New Student
document.getElementById("btn-post").addEventListener("click", async () => {
    const name = document.getElementById("post-name").value;
    const grade = document.getElementById("post-grade").value;

    if (!name || grade === "") return showMessage("post-result", "Please provide both name and grade.", true);

    try {
        const response = await fetch(BASE_URL, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ name: name.trim(), grade: parseFloat(grade) })
        });
        
        if (!response.ok) throw new Error("Failed to add student");
        const data = await response.json();
        showMessage("post-result", `Successfully added ${name} with grade ${data.grade || grade}.`);
        
        // Auto-refresh the table
        document.getElementById("btn-load-all").click();
    } catch (error) {
        showMessage("post-result", "Error: " + error.message, true);
    }
});

// Edit Student Grade
document.getElementById("btn-put").addEventListener("click", async () => {
    const name = document.getElementById("put-name").value;
    const grade = document.getElementById("put-grade").value;

    if (!name || grade === "") return showMessage("put-result", "Please provide both name and new grade.", true);

    try {
        const response = await fetch(`${BASE_URL}/${encodeName(name)}`, {
            method: "PUT",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ grade: parseFloat(grade) })
        });

        if (!response.ok) throw new Error("Failed to update grade");
        const data = await response.json();
        showMessage("put-result", `Successfully updated ${name}'s grade to ${data.grade || grade}.`);
        
        // Auto-refresh the table
        document.getElementById("btn-load-all").click();
    } catch (error) {
        showMessage("put-result", "Error: " + error.message, true);
    }
});

// Delete Student Grade
document.getElementById("btn-delete").addEventListener("click", async () => {
    const name = document.getElementById("delete-name").value;
    if (!name) return showMessage("delete-result", "Please enter a student name to delete.", true);

    if (!confirm(`Are you sure you want to delete ${name}?`)) return;

    try {
        const response = await fetch(`${BASE_URL}/${encodeName(name)}`, {
            method: "DELETE"
        });

        if (!response.ok) throw new Error("Failed to delete student");
        showMessage("delete-result", `Successfully deleted ${name}.`);
        
        // Auto-refresh the table
        document.getElementById("btn-load-all").click();
    } catch (error) {
        showMessage("delete-result", "Error: " + error.message, true);
    }
});