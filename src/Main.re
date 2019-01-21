type todo = {message: string};

type state = {
  newTodoText: string,
  newListText: string,
  todoLists: list(todo),
};

type action =
  | UpdateNewTodoText(string)
  | UpdateNewListText(string)
  | CreateTodo
  | DeleteTodo
  | SelectList;

let component = ReasonReact.reducerComponent("Main");

let mkStyle = ReactDOMRe.Style.make;

let inlineBlock = mkStyle(~display="inline-block");

let rstr = s => ReasonReact.string(s);

let make = _children => {
  ...component,
  initialState: () => {todoLists: [], newTodoText: "", newListText: ""},
  reducer: (action, state) =>
    switch (action) {
    | UpdateNewListText(text) =>
      ReasonReact.Update({...state, newListText: text})
    | UpdateNewTodoText(text) =>
      ReasonReact.Update({...state, newTodoText: text})
    | CreateTodo => ReasonReact.Update({...state, newTodoText: "a"})
    | DeleteTodo => ReasonReact.Update({...state, newTodoText: "a"})
    | SelectList => ReasonReact.Update({...state, newTodoText: "a"})
    },
  render: _self =>
    <section style={mkStyle(~width="70%", ~margin="auto", ())}>
      <h1 style={mkStyle(~textAlign="center", ())}> {rstr("Todo App")} </h1>
      <section style={inlineBlock(~width="25%", ())}>
        <h2> {rstr("Lists")} </h2>
      </section>
      <section style={inlineBlock(~width="75%", ())}>
        <h2> {rstr("Todos")} </h2>
      </section>
    </section>,
};
