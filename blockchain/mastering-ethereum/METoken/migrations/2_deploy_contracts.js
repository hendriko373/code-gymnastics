const METoken = artifacts.require("METoken");
const Ico = artifacts.require("Ico");

module.exports = function(deployer, network, accounts) {
  deployer.deploy(METoken, {from: accounts[0]}).then(
      function()
      {
          return deployer.deploy(
              Ico, METoken.address, accounts[0], web3.utils.toWei('2', 'ether'));
      });
};
