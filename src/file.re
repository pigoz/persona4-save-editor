type file;

let read: (file) => Js.Promise.t(Js.Typed_array.Uint8Array.t) = [%bs.raw {|
  function(file) {
    return new Promise(resolve => {
      const fr = new FileReader();
      fr.onload = function () {
        const data = fr.result;
        const xs = new Uint8Array(data);
        resolve(xs);
      }
      fr.readAsArrayBuffer(file);
    });
  }
|}];

/* I feel like promises have a really bad API in a typed language, curried
   function seems much better */
let reader = (callback, file) =>
  Js.Promise.(read(file)
    |> then_((xs) => {
      callback(xs);
      resolve ();
    })
  ) |> ignore;
