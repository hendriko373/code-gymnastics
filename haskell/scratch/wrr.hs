import Control.Monad.Trans.State

data Event = Event
    { load :: Integer
    , prior :: Integer
    , deadline :: Integer}
    deriving Show

-- Using the State monad
calcDeadlines1 :: [(Integer, Integer)] -> [Integer]
calcDeadlines1 prioritizedLoads = 
    go $ fmap (\(l, p) -> Event { load = l, prior = p, deadline = 0 }) prioritizedLoads
        where go events = if any ((>0) . load) events
                             then go $ execState stepForward1 events
                             else fmap deadline events

stepForward1 :: State [Event] ()
stepForward1 = do
    events <- get
    put $ fmap (\e -> e { prior = if load e > 0 then prior e else 0 }) events
    events' <- get
    let priors = fmap prior events'
    let step = minimum $ fmap h $ filter ((>0) . load) events'
                where h e = ceiling $ 
                                fromInteger (load e) / normalize (prior e) priors
    put $ fmap (\e -> 
        if load e > 0 
           then e 
               { load = load e 
                            - ceiling (fromInteger step * normalize (prior e) priors)
               , deadline = deadline e + step}
           else e) events'

-- Using the a function directly 
calcDeadlines2 :: [(Integer, Integer)] -> [Integer]
calcDeadlines2 prioritizedLoads = 
    go $ fmap (\(l, p) -> Event { load = l, prior = p, deadline = 0 }) prioritizedLoads
        where go events = if all ((<=0) . load) events
                             then fmap deadline events
                             else go $ stepForward3 events

stepForward2 :: [Event] -> [Event] 
stepForward2 = do
    updated <- \events -> fmap (\e -> e { prior = if load e > 0 then prior e else 0 }) events
    \_ -> 
        let priors = fmap prior updated
            step = minimum $ fmap h $ filter ((>0) . load) updated
                where h e = ceiling $ fromInteger (load e) / normalize (prior e) priors
         in fmap (\e -> 
             if load e > 0 
                then e 
                    { load = load e - ceiling (fromInteger step * normalize (prior e) priors)
                    , deadline = deadline e + step}
                else e) updated

stepForward3 :: [Event] -> [Event] 
stepForward3 events = 
    let updated = fmap (\e -> e { prior = if load e > 0 then prior e else 0 }) events
     in let priors = fmap prior updated
            step = minimum $ fmap h $ filter ((>0) . load) updated
                where h e = ceiling $ fromInteger (load e) / normalize (prior e) priors
         in fmap (\e -> 
             if load e > 0 
                then e 
                    { load = load e - ceiling (fromInteger step * normalize (prior e) priors)
                    , deadline = deadline e + step}
                else e) updated

normalize :: Fractional a => Integer -> [Integer] -> a
normalize p ps = fromInteger p / sum (fmap fromInteger ps)




