let component = ReasonReact.statelessComponent("Board");

let make = (~activeMole, ~molear, _children) => {
  ...component,
  render: _self =>
    <div className="board">
      {
        Belt.Array.range(0, 8)
        ->Belt.Array.map(key =>
            <div className="board-item" key={string_of_int(key)}>
              <div
                className={activeMole == key ? "mole visible" : "mole"}
                onClick={_ => activeMole == key ? molear() : ()}
              />
              <div className="ground" />
            </div>
          )
        ->ReasonReact.array
      }
    </div>,
};