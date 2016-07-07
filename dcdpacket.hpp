#ifndef DCDPACKET_HPP
#define DCDPACKET_HPP

#include <memory>

const int DCD_COMMAND_SIZE = 1;
const int DCD_DESTINATION_SIZE = 1;

const int DCD_DESTINATION_POSITION = 0;
const int DCD_COMMAND_POSITION = 1;
const int DCD_DATA_POSITION = 2;

template<class T>
class DCDPacket {
public:
    DCDPacket(T* data, const int& size) :
        _size(size),
        _data(data),
        _level(0)
    {

    }

    const T& getDestination()
    {
        return *(_data.get() + getDestinationPosition());
    }

    const T& getCommand()
    {
        return *(_data.get() + getCommandPosition());
    }

    const T& getData(const int& position)
    {
        return *(_data.get() + getDataPosition() + position);
    }

    const int getDataSize()
    {
        return _size - (_level*(DCD_DESTINATION_SIZE + DCD_COMMAND_SIZE));
    }

    DCDPacket<T> getNextLevelPacket()
    {
        DCDPacket<T> newPacket(_data, _size, _level);
        return newPacket;
    }

private:
    DCDPacket(std::shared_ptr<T> data, const int& size, const int& level) :
        _size(size),
        _data(data),
        _level(level+1)
    {

    }

    int getDestinationPosition()
    {
        return (_level*(DCD_DESTINATION_SIZE + DCD_COMMAND_SIZE)
                + DCD_DESTINATION_POSITION);
    }

    int getCommandPosition()
    {
        return (_level*(DCD_DESTINATION_SIZE + DCD_COMMAND_SIZE)
                + DCD_COMMAND_POSITION);
    }

    int getDataPosition()
    {
        return (_level*(DCD_DESTINATION_SIZE + DCD_COMMAND_SIZE)
                + DCD_DATA_POSITION);
    }

private:
    int _size;
    std::shared_ptr<T> _data;
    int _level;
};

#endif // DCDPACKET_HPP

