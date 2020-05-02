{-# LANGUAGE OverloadedStrings #-}
module Scotty where

import Web.Scotty
import Web.Scotty.Internal.Types (ActionT(..))
import Data.Monoid (mconcat)
import Control.Monad
import Control.Monad.Trans.Class
import Control.Monad.Trans.Reader
import Control.Monad.Trans.State.Lazy (StateT(..))
import Control.Monad.Trans.Except
import Control.Monad.IO.Class

main = scotty 3000 $ do
    get "/:word" $ do
    beam <- param "word"
--    (ActionT 
--        . (ExceptT . liftM Right) 
--        . (ReaderT . const) 
--        . (\m -> StateT (\s -> do
--                a <- m
--                return (a, s))
--            )) $ putStrLn "hello"
    liftIO $ putStrLn "hello"
    html $ mconcat ["<h1>Scotty, ", beam, " me up!</h1>"]
