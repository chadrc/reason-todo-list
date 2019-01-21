type todo = {message: string};

type todoList = {
  name: string,
  todos: list(todo),
};

type state = {
  newTodoText: string,
  newListText: string,
  selectedList: option(int),
  todoLists: list(todoList),
};

type action =
  | UpdateNewTodoText(string)
  | UpdateNewListText(string)
  | CreateTodo
  | CreateList
  | DeleteTodo
  | DeleteList
  | SelectList;

let component = ReasonReact.reducerComponent("Main");

let rstr = s => ReasonReact.string(s);

let make = _children => {
  ...component,
  initialState: () => {
    todoLists: [],
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
    | CreateList => ReasonReact.Update({...state, newTodoText: "a"})
    | DeleteTodo => ReasonReact.Update({...state, newTodoText: "a"})
    | DeleteList => ReasonReact.Update({...state, newTodoText: "a"})
    | SelectList => ReasonReact.Update({...state, newTodoText: "a"})
    },
  render: self =>
    <section className="container">
      <header> <h1 className="header"> {rstr("Todo App")} </h1> </header>
      <section className="main-view">
        <section className="left-column">
          <h2> {rstr("Lists")} </h2>
          <SimpleInputForm
            onInput={_event => self.send(UpdateNewListText("a"))}
            onSubmit={_event => self.send(CreateList)}
            buttonText={rstr("Create List")}
          />
        </section>
        {switch (self.state.selectedList) {
         | None => ReasonReact.null
         | Some(_listIndex) =>
           <section className="right-column">
             <h2> {rstr("Todos")} </h2>
             <SimpleInputForm
               onInput={_event => self.send(UpdateNewTodoText("a"))}
               onSubmit={_event => self.send(CreateTodo)}
               buttonText={rstr("Create Todo")}
             />
           </section>
         }}
      </section>
    </section>,
};
