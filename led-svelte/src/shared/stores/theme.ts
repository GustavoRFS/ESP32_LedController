import { writable } from "svelte/store";

type Theme = "light" | "dark";

function detectColorScheme() {
  var theme: Theme = "light";

  if (localStorage.getItem("theme") === "dark") {
    theme = "dark";
  } else if (localStorage.getItem("theme") === "light") {
    theme = "light";
  } else if (!window.matchMedia) {
    return "light";
  } else if (window.matchMedia("(prefers-color-scheme: dark)").matches) {
    theme = "dark";
  }

  return theme;
}

const themeStore = writable<Theme>(detectColorScheme());

themeStore.subscribe((theme) => {
  localStorage.setItem("theme", theme);
  document.documentElement.setAttribute("data-theme", theme);
});

export default themeStore;
