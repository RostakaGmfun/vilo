-- Actor script

--called on actor creation
--return: nothing
function create()
    print("In create")
end

--called every tick (frame yeah)
--return:
-- 0 or nil - continue runnig actor
-- else - destroy the actor - will call dectroy() function
function update()
    print("On update")
end

--called on actor destroy
--returns - nothing
function destroy()
    print("On Destroy")
end
