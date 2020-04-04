# Weighted round robin

def deadlines(loads, priors, delta):
    """
    Calculates sensible deadlines for a set work items based on weighted round
    robin. Deadlines are estimated by the time an event should be finished if
    using weighted round robin to schedule the incoming loads.
    """
    result = [0] * len(loads)
    done = [0] * len(loads)
    nonzero = [p if p != 0 else 0.01 for p in priors]

    time = 0
    while any(not is_finished(t[0], t[1]) for t in zip(done, loads)):
        normal = normalized((pushforward(nonzero, done, loads)))
        done = [t[0] + t[1]*delta for t in zip(done, normal)]
        time = time + delta
        result = [
                time if is_finished(t[0], t[1]) and t[2] == 0 else t[2] 
                for t in zip(done, loads, result)]

    return [round(r, 0) for r in result]

def pushforward(priors, done, loads):
    return [0 if is_finished(t[0], t[1]) else t[2] for t in zip(done, loads, priors)]

def normalized(priors):
    return [p / sum(priors) for p in priors]

def is_finished(done, load):
    return done >= load
