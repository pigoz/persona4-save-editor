let handleFileSelection = [%bs.raw {|
  function(event, _self) {
    const file = event.target.files[0];
    console.log("selected", file);
    const fr = new FileReader();
    fr.onload = function () {
      const data = fr.result;
      const xs = new Uint8Array(data);
      const name = xs.slice(16, 16 + (8 * 2))
        // this is big-endian because lol psvita, ignore the most significant
        // byte since it's garbage anyway
        .filter((x, idx) => idx % 2 !== 0)
        // -96 not sure why but the least significant part in the unicode word
        // is saved by summing 96/0x60 to the actual unicode/ascii value
        .map(x => x - 0x60);
      console.log(name);
      console.log(new TextDecoder("utf-8").decode(name));
    }
    fr.readAsArrayBuffer(file);
  }
|}];
