type todo = {message: string};

type todoList = {
  id: int,
  name: string,
  todos: array(todo),
};

type state = {
  newTodoText: string,
  newListText: string,
  selectedList: option(int),
  todoLists: array(todoList),
};

type action =
  | UpdateNewTodoText(string)
  | UpdateNewListText(string)
  | CreateTodo
  | CreateList
  | DeleteTodo
  | DeleteList
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
    | CreateTodo => ReasonReact.Update({...state, newTodoText: "a"})
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
    | DeleteTodo => ReasonReact.Update({...state, newTodoText: "a"})
    | DeleteList => ReasonReact.Update({...state, newTodoText: "a"})
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
          <ul>
            {ReasonReact.array(
               self.state.todoLists
               |> Js.Array.map(item =>
                    <li
                      onClick={_event => self.send(SelectList(item.id))}
                      key={string_of_int(item.id)}>
                      {rstr(item.name)}
                    </li>
                  ),
             )}
          </ul>
        </section>
        {switch (self.state.selectedList) {
         | None => ReasonReact.null
         | Some(listIndex) =>
           <section className="right-column">
             <h2> {rstr(self.state.todoLists[listIndex].name)} </h2>
             <SimpleInputForm
               onChange={value => self.send(UpdateNewTodoText(value))}
               onSubmit={() => self.send(CreateTodo)}
               value={self.state.newTodoText}
               buttonText={rstr("Create Todo")}
             />
           </section>
         }}
      </section>
    </section>,
};
