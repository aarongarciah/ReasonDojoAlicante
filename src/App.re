type action =
  | Start
  | ChangeActiveMole(int)
  | Reset
  | Molear;

type state =
  | Stopped
  | Playing(int /* score */, int /*activeMole*/, int /* setInterval */);

let component = ReasonReact.reducerComponent("App");

let getScore = state =>
  switch (state) {
  | Playing(score, _activeMole, _interval) => score
  | _ => 0
  };

let getActiveMole = state =>
  switch (state) {
  | Playing(_score, activeMole, _interval) => activeMole
  | _ => 0
  };

let getNewActiveMole = _ => Js.Math.random_int(0, 9);

let make = _children => {
  ...component,
  initialState: () => Stopped,
  reducer: (action, state) =>
    switch (action) {
    | ChangeActiveMole(activeMole) =>
      ReasonReact.Update(Playing(getScore(state), activeMole, 0))
    | Start =>
      ReasonReact.UpdateWithSideEffects(
        Playing(0, 0, 0),
        (
          self => {
            let _ =
              Js.Global.setInterval(
                () => getNewActiveMole()->ChangeActiveMole |> self.send,
                1000,
              );
            ();
          }
        ),
      )
    | Reset => ReasonReact.Update(Stopped)
    | Molear =>
      ReasonReact.Update(
        Playing(getScore(state) + 100, getNewActiveMole(), 0),
      )
    },
  render: ({state, send}) =>
    <div className="app">
      <div className="game">
        {
          switch (state) {
          | Stopped =>
            <Button text="Start Game" onClick=(_click => send(Start)) />
          | Playing(score, activeMole, _interval) =>
            <div>
              <h1> {string_of_int(score) |> ReasonReact.string} </h1>
              <Board activeMole molear=(_ => send(Molear)) />
              <br />
              <Button text="Reset" onClick=(_click => send(Reset)) />
            </div>
          }
        }
      </div>
    </div>,
};