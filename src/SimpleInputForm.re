let component = ReasonReact.statelessComponent("SimpleInputForm");

let make = (~onChange, ~onSubmit, ~value, ~buttonText, _children) => {
  let submit = (event, _self) => {
    ReactEvent.Mouse.preventDefault(event);
    onSubmit();
  };
  {
    ...component,
    render: self =>
      <form>
        <input
          value
          onChange={event => onChange(ReactEvent.Form.target(event)##value)}
        />
        <button onClick={self.handle(submit)}> buttonText </button>
      </form>,
  };
};
