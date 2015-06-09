print "In \"Main.lua\""

function create() 
    actor = vilo.Actor.New("Actor.lua", "Dude")
    print(actor.__object__)
    actor:Hello() 
    actor:sayHello()
    print(actor.health)
    actor:create()
    return 0
end

function update(dt)

end

function destroy()
    actor:destroy()
end
