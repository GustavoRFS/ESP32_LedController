import axios from "axios";

export default axios.create({
  baseURL: "https://api.github.com/repos/GustavoRFS/ESP32_LedController/",
});
