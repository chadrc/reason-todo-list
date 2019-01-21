let component = ReasonReact.statelessComponent("SimpleInputForm");

let make = (~onInput, ~onSubmit, ~buttonText, _children) => {
  ...component,
  render: _self =>
    <form>
      <input onInput={_event => onInput("a")} />
      <button onClick={_event => onSubmit()}> buttonText </button>
    </form>,
};
