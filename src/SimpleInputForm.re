let component = ReasonReact.statelessComponent("SimpleInputForm");

let make = (~onChange, ~onSubmit, ~buttonText, _children) => {
  let submit = (event, _self) => {
    ReactEvent.Mouse.preventDefault(event);
    onSubmit();
  };
  {
    ...component,
    render: self =>
      <form>
        <input
          onChange={event => onChange(ReactEvent.Form.target(event)##value)}
        />
        <button onClick={self.handle(submit)}> buttonText </button>
      </form>,
  };
};
