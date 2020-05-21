pragma solidity ^0.6.0;

import 'openzeppelin-solidity/contracts/token/ERC20/ERC20.sol';

contract METoken is ERC20('Mastering Ethereum Token', 'MET') {

    uint constant _initial_supply = 2100000000;

    constructor() public
    {
        _setupDecimals(2);
        _mint(msg.sender, _initial_supply);
    }
}
