print "In \"Main.lua\""

function create() 
    actor = vilo.Actor.New("Actor.lua", "Dude")
    print(actor.__object__)
    actor:Hello() 
    actor:sayHello()
    print(actor.health)
end

function update(dt)
    actor:update(dt)
end

function destroy()
    actor:destroy()
end
