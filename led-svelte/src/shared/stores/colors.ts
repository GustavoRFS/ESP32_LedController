import { writable } from "svelte/store";
import type { Color, Favorite, Gradient } from "../@types/Color";

function getFavorites() {
  const favorites = localStorage.getItem("favorites");
  if (favorites) {
    return JSON.parse(favorites);
  }
  return [];
}

type ColorStoreType = {
  color: Color;
  gradient: Gradient[];
  favorites: Favorite[];
};

const colorStore = writable<ColorStoreType>({
  color: { r: 0, g: 255, b: 170 },
  gradient: [
    { color: { r: 0, g: 255, b: 170 }, percentage: 0 },
    { color: { r: 0, g: 255, b: 170 }, percentage: 100 },
  ],
  favorites: getFavorites(),
});

colorStore.subscribe((state) => {
  localStorage.setItem("favorites", JSON.stringify(state.favorites));
});

export default colorStore;
