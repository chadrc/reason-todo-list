open ReasonReact;

let component = statelessComponent("Main");

let make = _children => {
  ...component,
  render: _self =>
    <section>
      <h1> {string("Todo App")} </h1>
      <section> <h2> {string("")} </h2> </section>
    </section>,
};
