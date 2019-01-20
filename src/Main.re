let component = ReasonReact.statelessComponent("Main");

let make = _children => {
  ...component,
  render: _self =>
    <section>
      <h1 style={ReactDOMRe.Style.make(~textAlign="center", ())}>
        {ReasonReact.string("Todo App")}
      </h1>
      <section> <h2> {ReasonReact.string("")} </h2> </section>
    </section>,
};
