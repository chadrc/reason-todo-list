let component = ReasonReact.statelessComponent("Main");

let mkStyle = ReactDOMRe.Style.make;

let inlineBlock = mkStyle(~display="inline-block");

let rstr = s => ReasonReact.string(s);

let make = _children => {
  ...component,
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
