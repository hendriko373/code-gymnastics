pragma solidity ^0.6.0;

import '../contracts/METoken.sol' as MET;
import 'openzeppelin-solidity/contracts/math/SafeMath.sol';

contract Ico 
{
    using SafeMath for uint256;

    address payable _owner;
    MET.METoken _tokens;
    uint256 _price;

    constructor(
        address tokens, 
        address payable owner,
        uint256 price) public
    {
        _owner = owner;
        _tokens = MET.METoken(tokens);
        _price = price;
    }

    function buy() public payable
    {
        uint256 qty = msg.value.div(_price);
        uint256 rem = msg.value.mod(_price);
        
        _tokens.transferFrom(_owner, msg.sender, qty);
        _owner.transfer(msg.value.sub(rem));

        msg.sender.transfer(rem);
    }

    receive() external payable
    {
    }
}
