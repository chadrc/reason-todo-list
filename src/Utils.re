let stopEvent = event => {
  ReactEvent.Mouse.preventDefault(event);
  ReactEvent.Mouse.stopPropagation(event);
};

let removeIndex = (index: int, a: array('a)) => {
  ignore(Js.Array.spliceInPlace(~pos=index, ~remove=1, ~add=[||], a));
};
