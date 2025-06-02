import { marked } from "marked";

function renderMarkdown() {
    const markdownBlocks = document.querySelectorAll(".markdown");

    markdownBlocks.forEach(async (block) => {
        const raw = block.textContent || "";
        const html = await marked.parse(raw);
        block.innerHTML = html;
    });
}

window.addEventListener("DOMContentLoaded", () => {
    renderMarkdown();
});
