import streamlit as st

# --- Page setup ---
st.set_page_config(page_title="Task Tracker", page_icon="✅")

# --- Store tasks in session state ---
if "tasks" not in st.session_state:
    st.session_state["tasks"] = []

# --- Sidebar navigation ---
st.sidebar.title("Navigation")
page = st.sidebar.radio("Go to:", ["Home", "Add Task", "View Tasks", "About"])

# --- Home Page ---
if page == "Home":
    st.title("🏠 Home Page")
    st.write("Welcome to the Simple Task Tracker!")
    st.info("Use the sidebar to add and view tasks.")

# --- Add Task Page ---
elif page == "Add Task":
    st.title("📝 Add a Task")
    task = st.text_input("Enter task name:")
    desc = st.text_area("Enter short description:")
    add = st.button("Add Task")

    if add:
        if task.strip() == "":
            st.error("⚠ Task name cannot be empty.")
        else:
            st.session_state["tasks"].append({"Task": task, "Description": desc, "Status": "Pending"})
            st.success(f"✅ Task '{task}' added successfully!")

# --- View Tasks Page ---
elif page == "View Tasks":
    st.title("📋 View Tasks")
    tasks = st.session_state["tasks"]

    if not tasks:
        st.warning("No tasks added yet.")
    else:
        for i, t in enumerate(tasks):
            st.write(f"**{i+1}. {t['Task']}** — {t['Description']}  ✅ *{t['Status']}*")

        if st.button("Clear All Tasks"):
            st.session_state["tasks"].clear()
            st.warning("All tasks cleared.")

# --- About Page ---
elif page == "About":
    st.title("ℹ️ About")
    st.write("This simple app lets you add and view tasks using Streamlit.")
    st.caption("Designed for practical/viva demonstration 💡")
