import streamlit as st

if "tasks" not in st.session_state:
    st.session_state["tasks"] = []

st.sidebar.title("Navigation")
page = st.sidebar.radio("Go to:",["Home","Add tasks","View tasks","About"])

if page == "Home":
    st.title("Home page")
    st.write("Landing page to know the contents of the site")
    st.info("use the sidebar to access the features")

elif page == "Add tasks":
    st.title("Add task")
    task = st.text_input("Enter the name of the task")
    desc = st.text_area("Enter the description of the task")
    add = st.button("Add task")

    if add:
        if not task:
            st.error("task is empty")
        else:
            st.session_state["tasks"].append({"Tasks":task,"Description":desc})
            st.success("task added successfully")

elif page == "View tasks":
    st.title("View tasks")
    task = st.session_state["tasks"]
    if not task:
        st.error("task is empty")
    else:
        for i,t in enumerate(task):
            st.write(f"{i+1}.{t["Tasks"]} - {t["Description"]}")
        
        if st.button("clear tasks"):
            st.session_state["tasks"].clear()
            st.warning("tasks deleted")

elif page == "About":
    st.title("About page")
    st.write("contains details of the site")
    st.caption("designed using streamlit")