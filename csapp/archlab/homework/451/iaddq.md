
|phase|iaddq V,rB|
|--|--|
|F|icode:ifun = M1[PC]; rA:rB = M1[PC+1]; valC = M8[PC+2]; valP = PC + 10;|
|D|valB = R[rB]|
|E|valE = valB + valC; set CC|
|M||
|W|R[rB] = valE|
|PC|PC = valP|