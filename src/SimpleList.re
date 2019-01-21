type list_item = {
  id: int,
  text: string,
};

let component = ReasonReact.statelessComponent("SimpleList");

let make = (~items: array(list_item), ~onClick=?, _children) => {
  ...component,
  render: _self =>
    <ul>
      {ReasonReact.array(
         items
         |> Js.Array.map(item =>
              <li
                onClick={_event =>
                  switch (onClick) {
                  | None => ()
                  | Some(action) => action(item.id)
                  }
                }
                key={string_of_int(item.id)}>
                {ReasonReact.string(item.text)}
              </li>
            ),
       )}
    </ul>,
};
