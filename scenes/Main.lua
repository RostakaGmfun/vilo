print "In \"Main.lua\""

function create() 
    actor = vilo.Actor.New("Actor.lua", "Dude")
    actor:Hello() 
    actor:sayHello()
    return 0
end

function update(dt)

end

function destroy()
    actor:destroy()
end
