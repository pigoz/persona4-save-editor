/* this might pose a problem because of value restriction, but it seems to
 * work for now. see: http://mlton.org/ValueRestriction */
let (>>) = (f, g, x) => g(f(x));
