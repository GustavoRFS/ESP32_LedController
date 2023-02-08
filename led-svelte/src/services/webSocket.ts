const WebSocketURL = "ws://pp.local/api/ws";

let ws: WebSocket;
const events: { eventType: string; cb: (event: any) => void }[] = [];

const onMessage = <T>(eventType: string, cb: (event: T) => void) => {
  events.push({ eventType, cb });
};

const send = (data: any) => {
  try {
    ws.OPEN && ws.send(JSON.stringify(data));
  } catch (err) {}
};

const openWs = () => {
  ws = new WebSocket(WebSocketURL);

  ws.onopen = () => {
    events.forEach((event) =>
      ws.addEventListener("message", (message) => {
        const eventData = JSON.parse(message.data);

        if (event.eventType === eventData.event) event.cb(eventData.data);
      })
    );
  };

  ws.onclose = () => {
    openWs();
  };
};

openWs();

export default {
  onMessage,
  send,
};
