type todo = {
  id: int,
  message: string,
};

type todo_list = {
  id: int,
  name: string,
  todos: array(todo),
};

type state = {
  newTodoText: string,
  newListText: string,
  selectedList: option(int),
  todoLists: array(todo_list),
};

type action =
  | UpdateNewTodoText(string)
  | UpdateNewListText(string)
  | CreateTodo
  | CreateList
  | DeleteTodo(int)
  | DeleteList(int)
  | SelectList(int);

let component = ReasonReact.reducerComponent("Main");

let rstr = s => ReasonReact.string(s);

let currentId = ref(0);

let genId = () => {
  let id = currentId^;
  currentId := currentId^ + 1;
  id;
};

let make = _children => {
  ...component,
  initialState: () => {
    todoLists: [||],
    newTodoText: "",
    newListText: "",
    selectedList: None,
  },
  reducer: (action, state) =>
    switch (action) {
    | UpdateNewListText(text) =>
      ReasonReact.Update({...state, newListText: text})
    | UpdateNewTodoText(text) =>
      ReasonReact.Update({...state, newTodoText: text})
    | CreateTodo =>
      switch (state.selectedList) {
      | None => ReasonReact.NoUpdate
      | Some(listIndex) =>
        let selectedList = state.todoLists[listIndex];
        ignore(
          selectedList.todos
          |> Js.Array.push({id: genId(), message: state.newTodoText}),
        );
        ReasonReact.Update({
          ...state,
          todoLists: state.todoLists,
          newTodoText: "",
        });
      }
    | CreateList =>
      let trimmed = Js.String.trim(state.newListText);
      if (trimmed != "") {
        let newList = {id: genId(), name: state.newListText, todos: [||]};
        ignore(Js.Array.push(newList, state.todoLists));
        ReasonReact.Update({
          ...state,
          todoLists: state.todoLists,
          newListText: "",
        });
      } else {
        ReasonReact.NoUpdate;
      };
    | DeleteTodo(id) =>
      switch (state.selectedList) {
      | None => ReasonReact.NoUpdate
      | Some(listIndex) =>
        let selectedList = state.todoLists[listIndex];
        (
          selectedList.todos
          |> Js.Array.findIndex((todo: todo) => todo.id == id)
        )
        ->Utils.removeIndex(selectedList.todos);

        ReasonReact.Update({...state, todoLists: state.todoLists});
      }
    | DeleteList(id) =>
      (state.todoLists |> Js.Array.findIndex(item => item.id == id))
      ->Utils.removeIndex(state.todoLists);

      ReasonReact.Update({...state, todoLists: state.todoLists});
    | SelectList(id) =>
      let selectedList =
        Some(state.todoLists |> Js.Array.findIndex(item => item.id == id));
      ReasonReact.Update({...state, selectedList});
    },
  render: self =>
    <section className="container">
      <header> <h1 className="header"> {rstr("Todo App")} </h1> </header>
      <section className="main-view">
        <section className="left-column">
          <h2> {rstr("Lists")} </h2>
          <SimpleInputForm
            onChange={value => self.send(UpdateNewListText(value))}
            onSubmit={() => self.send(CreateList)}
            value={self.state.newListText}
            buttonText={rstr("Create List")}
          />
          <SimpleList
            onDeleteClick={id => self.send(DeleteList(id))}
            onClick={id => self.send(SelectList(id))}
            items={
              self.state.todoLists
              |> Js.Array.map((todo: todo_list) =>
                   ({id: todo.id, text: todo.name}: SimpleList.list_item)
                 )
            }
          />
        </section>
        {switch (self.state.selectedList) {
         | None => ReasonReact.null
         | Some(listIndex) =>
           let selectedList = self.state.todoLists[listIndex];
           <section className="right-column">
             <h2> {rstr(selectedList.name)} </h2>
             <SimpleInputForm
               onChange={value => self.send(UpdateNewTodoText(value))}
               onSubmit={() => self.send(CreateTodo)}
               value={self.state.newTodoText}
               buttonText={rstr("Create Todo")}
             />
             <SimpleList
               onDeleteClick={id => self.send(DeleteTodo(id))}
               onClick={id => Js.log("selected item " ++ string_of_int(id))}
               items={
                 selectedList.todos
                 |> Js.Array.map((todo: todo) =>
                      (
                        {id: todo.id, text: todo.message}: SimpleList.list_item
                      )
                    )
               }
             />
           </section>;
         }}
      </section>
    </section>,
};
