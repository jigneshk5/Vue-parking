$(function () {
    var client = mqtt.connect('mqtt://jigneshk5:jignesh12345@broker.shiftr.io', {
        clientId: 'javascript'
    });
    client.unsubscribe('status/parking/slot1');
    client.unsubscribe('status/parking/slot2');
    client.on('connect', function () {
        console.log('client has connected!');
    });

    client.on('message', function (topic, message) {
        console.log('new message:', topic, message.toString());
    });

    $('#subscribe1').click(function () {
        client.subscribe('status/parking/slot1');
    });
    $('#subscribe2').click(function () {
        client.subscribe('status/parking/slot2');
    });
    $('#unsubscribe1').click(function () {
        client.unsubscribe('status/parking/slot1');
    });
    $('#unsubscribe2').click(function () {
        client.unsubscribe('status/parking/slot2');
    });
    $('#button1').click(function () {
        client.publish('status/availability', 'true');
    });
    $('#button2').click(function () {
        client.publish('status/availability', 'false');
    })
    $('#permit1').click(function () {
        client.publish('status/permit', 'true');
    });
    $('#permit2').click(function () {
        client.publish('status/permit', 'false');
    })
    $('#booking1').click(function () {
        client.publish('status/booking', 'true');
    });
    $('#booking2').click(function () {
        client.publish('status/booking', 'false');
    })
    $('#parked1').click(function () {
        client.publish('status/parked', 'true');
    });
    $('#parked2').click(function () {
        client.publish('status/parked', 'false');
    })
})