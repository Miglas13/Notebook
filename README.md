# Notebook
A simple notebook developed using C language.

Objective

The objective of this project is the develop of an interactive application in C that allows the management of contacts and tasks. The application allows the insertion and management of contacts and tasks, and also, consulting some task or contact as, for example, to know what are the tasks scheduled for a certain period of time.

Execution of the application: 

First, you need to compile using the command cc -o project.c project. Then, execute ./project.

It will appear a menu with these options:

1-Contactos
2-Tarefas
0-Terminar

In contacts you will have to choose between:

1-Acrescentar COntacto - To add a contact. You will need to insert name (nome), address(morada), email, phone number (nº de telemovel) and what is the category of the contact: friends (Amigos), Family (Familia), Work (Trabalho), Net.

2-Eliminar Contacto - To erase a contact. You will only need the name of the contact and a confirmation message will appear.

3-Alterar Contacto - To edit a contact. It will give a menu to choose what to edit in that contact.

4-Pesquisar Contact - To search for a determined contact. It's possible to search by name, category or number of phone. 

0-Terminar - To go back to previous menu.

In Tasks you will have to choose between:

1-Acrescentar Tarefa - To add a task. You will need to insert a title (titulo), the place (local), a brief description (descrição), date (data) and the category: work (Trabalho), Leisure (Lazer), Home (casa) and Sports (Desporto).

2-Eliminar Tarefa - To erase a task. You will only need the name of the task and a confirmation message will appear.

3-Alterar Tarefa - To edit a task. It will give a menu to choose what to edit in that task.

4-Pesquisar Tarefa - To search for a task. It's possible to search by title, date, category or state.

0-Terminar - To go back to previous menu.

It was used a simple search for the searches and BubbleSort for the sort of the contacts and tasks.
