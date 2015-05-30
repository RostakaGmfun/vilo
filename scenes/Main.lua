print "In \"Main.lua\""

function loadenv(file)
    local newenv = {}
    setmetatable(newenv, { __index=_G })
    loadfile(file, bt, newenv)()
    return newenv
end

function create() 
    actor = vilo.Actor.New("Actor.lua", "Dude")
    print(actor.__object__)
--    print "before actor.create()"
--    actor.create()
--    print "after actor.create()"
--    actor = {}
--    setmetatable(actor, {Actor})
    actor.Hello()
end

function update(dt)
    actor.update(dt)
end

function destroy()
    actor.destroy()
end
