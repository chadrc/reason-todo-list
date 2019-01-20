open ReasonReact;

let component = statelessComponent("Main");

[%mui.withStyles
  "StyledMain"({alignCenter: ReactDOMRe.Style.make(~textAlign="center", ())})
];

let make = _children => {
  ...component,
  render: _self =>
    <StyledMain>
      ...{classes =>
        <section>
          <h1 className={classes.alignCenter}> {string("Todo App")} </h1>
          <section> <h2> {string("")} </h2> </section>
        </section>
      }
    </StyledMain>,
};
