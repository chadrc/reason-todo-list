let stopEvent = event => {
  ReactEvent.Mouse.preventDefault(event);
  ReactEvent.Mouse.stopPropagation(event);
};
