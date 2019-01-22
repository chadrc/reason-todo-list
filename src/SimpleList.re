type list_item = {
  id: int,
  text: string,
};

let component = ReasonReact.statelessComponent("SimpleList");

let make = (~items: array(list_item), ~onClick=?, ~onDeleteClick, _children) => {
  ...component,
  render: _self =>
    <ul>
      {ReasonReact.array(
         items
         |> Js.Array.map(item =>
              <li
                onClick={event => {
                  Utils.stopEvent(event);

                  switch (onClick) {
                  | None => ()
                  | Some(action) => action(item.id)
                  };
                }}
                key={string_of_int(item.id)}>
                {ReasonReact.string(item.text)}
                <button
                  onClick={event => {
                    Utils.stopEvent(event);
                    onDeleteClick(item.id);
                  }}>
                  {%raw
                   {|'\u00D7'|}}
                </button>
              </li>
            ),
       )}
    </ul>,
};
