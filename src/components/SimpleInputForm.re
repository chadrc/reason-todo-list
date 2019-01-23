let component = ReasonReact.statelessComponent("SimpleInputForm");

let make = (~onChange, ~onSubmit, ~value, ~buttonText, _children) => {
  ...component,
  render: _self =>
    <form>
      <input
        value
        onChange={event => onChange(ReactEvent.Form.target(event)##value)}
      />
      <button
        onClick={event => {
          Utils.stopEvent(event);
          onSubmit();
        }}>
        buttonText
      </button>
    </form>,
};
